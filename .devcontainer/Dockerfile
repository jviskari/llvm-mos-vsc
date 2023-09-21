
FROM ubuntu:latest

# Install the necessary dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    ninja-build \
    python3 \
    python3-pip \
    xxd \
    cc1541 \
    bsdmainutils \
    64tass \
    cc65 \
    xa65 \ 
    acme

WORKDIR /tmp

# Clone the LLVM repository
RUN git clone https://github.com/llvm-mos/llvm-mos-sdk.git

ARG SDK_PATH=/mos-sdk
ENV MOS_SDK_PATH=$SDK_PATH

RUN cd llvm-mos-sdk && \
    mkdir build && \
    cd build && \
    cmake -G "Ninja" -DCMAKE_INSTALL_PREFIX=$SDK_PATH .. && \
    ninja install



RUN git clone https://bitbucket.org/magli143/exomizer.git

RUN make -C exomizer/src && cp exomizer/src/exomizer /usr/bin  && cp exomizer/src/exobasic /usr/bin 

# Set user and group
ARG user=devel
ARG group=devel
ARG uid=1000
ARG gid=1000
RUN groupadd -g ${gid} ${group}
RUN useradd -m -u ${uid} -g ${gid} -s /bin/bash ${user}

# Switch to non-root user

ENV PATH=$PATH:$MOS_SDK_PATH/bin

USER ${user}:${group}
WORKDIR /home/${user}

# Set the default command to run when the container starts

CMD ["bash"]
