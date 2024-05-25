# Use the latest Debian image
FROM debian:latest

# Install dependencies
RUN apt-get update && apt-get install -y \
    wget \
    gnupg \
    lsb-release \
    software-properties-common \
    cmake \
    ninja-build \
    git \
	vim \
    && rm -rf /var/lib/apt/lists/*

# Dynamically add the official LLVM repository based on the Debian codename
RUN CODENAME=$(lsb_release -cs) \
    && echo "deb http://apt.llvm.org/${CODENAME}/ llvm-toolchain-${CODENAME} main" > /etc/apt/sources.list.d/llvm.list \
    && wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add - \
    && apt-get update

# Download and run the LLVM installation script
RUN wget https://apt.llvm.org/llvm.sh && chmod +x llvm.sh && ./llvm.sh all

# Clean up
RUN rm llvm.sh

# Detect llvm version and create symlinks
RUN llvm_version=$(ls /usr/bin | grep clang++ | tr -d 'clang++-') \
    && ln -s /usr/bin/clang-$llvm_version /usr/bin/clang \
    && ln -s /usr/bin/clang++-$llvm_version /usr/bin/clang++ \
	&& rm /usr/bin/cc \
    && ln -s /usr/bin/clang-$llvm_version /usr/bin/cc \
    && ln -s /usr/bin/clang++-$llvm_version /usr/bin/c++

# Add environment variables directly to Dockerfile
ENV CC=/usr/bin/clang
ENV CXX=/usr/bin/clang++

COPY test.sh .
COPY test.cpp .

RUN chmod +x test.sh && ./test.sh

# Start an interactive bash shell
CMD ["/bin/bash"]
