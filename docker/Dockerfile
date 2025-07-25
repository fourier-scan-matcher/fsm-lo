FROM osrf/ros:kinetic-desktop
MAINTAINER Alexandros Philotheou alefilot@auth.gr
# ------------------------------------------------------------------------------
RUN apt-get update
RUN apt-get install -y \
  sudo apt-utils \
  build-essential \
  g++ \
  git \
  libfftw3-dev \
  libcgal-dev=4.7-4 \
  libcgal-qt5-dev=4.7-4 \
  libboost-random-dev \
  curl \
  python-catkin-tools \
  python-rosdep \
  python-rosinstall \
  python-rosinstall-generator \
  python-wstool \
  build-essential \
  python-rosdep \
  ros-kinetic-tf2-geometry-msgs
# ------------------------------------------------------------------------------
# Use bash and create user
# https://roboticseabass.com/2023/07/09/updated-guide-docker-and-ros2/
RUN rm /bin/sh && ln -s /bin/bash /bin/sh
ENV USER=fsmlo
RUN useradd --create-home ${USER}                                           && \
    echo ${USER} ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/${USER}         && \
    chmod 0440 /etc/sudoers.d/${USER}                                       && \
    mkdir -p /home/${USER}
USER ${USER}
WORKDIR /home/${USER}
# ------------------------------------------------------------------------------
RUN mkdir -p /home/${USER}/catkin_ws/src
COPY --chown=${USER}:${USER} ../fsm_lo/ /home/${USER}/catkin_ws/src/fsm_lo/
RUN rosdep update
# ------------------------------------------------------------------------------
RUN cd /home/${USER}/catkin_ws                                              && \
    export CC=gcc                                                           && \
    export CXX=g++                                                          && \
    alias g++='g++ -std=c++11'                                              && \
    alias clang++='clang++ -std=c++11'                                      && \
    source /opt/ros/kinetic/setup.bash                                      && \
    catkin build fsm_lo
# ------------------------------------------------------------------------------
# The next five lines + the entrypoint command will make sure that
# when the container is run the fsm node is roslaunched immediately
RUN echo "#!/bin/bash"                                      > /home/${USER}/fsm_launch.sh
RUN echo "source /opt/ros/kinetic/setup.bash"              >> /home/${USER}/fsm_launch.sh
RUN echo "source /home/${USER}/catkin_ws/devel/setup.bash" >> /home/${USER}/fsm_launch.sh
RUN echo "roslaunch fsm_lo avanti.launch"                  >> /home/${USER}/fsm_launch.sh
RUN chmod +x /home/${USER}/fsm_launch.sh
# ------------------------------------------------------------------------------
ENTRYPOINT bash /home/${USER}/fsm_launch.sh
