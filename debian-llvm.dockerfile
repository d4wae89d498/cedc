FROM debian:12-slim

# Set environment variables
ENV DEBIAN_FRONTEND=noninteractive

# Install necessary packages
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    build-essential \
    curl \
    git \
    vim \
    python3 \
    python3-pip \
    wget \
    zlib1g-dev \
    libzstd-dev \
    libcurl4-openssl-dev \
    libxml2-dev \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Dynamically add the official LLVM repository based on the Debian codename
RUN CODENAME=$(lsb_release -cs) \
	&& echo "deb http://apt.llvm.org/${CODENAME}/ llvm-toolchain-${CODENAME} main" > /etc/apt/sources.list.d/llvm.list \
	&& wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add - \
	&& apt-get update

# Download and run the LLVM installation script
RUN wget https://apt.llvm.org/llvm.sh && chmod +x llvm.sh && ./llvm.sh 18 all

# Clean up
RUN rm llvm.sh

# Detect llvm version and create symlinks
RUN llvm_version=$(ls /usr/bin | grep clang++ | tr -d 'clang++-') \
	&& ln -s /usr/bin/clang-$llvm_version /usr/bin/clang \
	&& ln -s /usr/bin/clang++-$llvm_version /usr/bin/clang++ \
	&& ln -s /usr/bin/llvm-config-$llvm_version /usr/bin/llvm-config \
	&& rm /usr/bin/cc \
	&& ln -s /usr/bin/clang-$llvm_version /usr/bin/cc \
	&& ln -s /usr/bin/clang++-$llvm_version /usr/bin/c++

# Add environment variables directly to Dockerfile
ENV CC=/usr/bin/clang
ENV CXX=/usr/bin/clang++

COPY test/llvm/test.sh .
COPY test/llvm/test.cpp .

RUN chmod +x test.sh && ./test.sh

# Start an interactive bash shell
CMD ["/bin/bash"]
