FROM debian:bookworm-slim

# Install dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
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
    && apt-get update \
    && apt-get install -y --no-install-recommends \
    clang \
    lldb \
    lld \
    clang-tools \
    && rm -rf /var/lib/apt/lists/*

# Create symlinks for clang and llvm
RUN llvm_version=$(ls /usr/bin | grep clang++ | tr -d 'clang++-') \
    && ln -s /usr/bin/clang-$llvm_version /usr/bin/clang \
    && ln -s /usr/bin/clang++-$llvm_version /usr/bin/clang++ \
    && ln -s /usr/bin/llvm-config-$llvm_version /usr/bin/llvm-config \
    && ln -s /usr/bin/clang-$llvm_version /usr/bin/cc \
    && ln -s /usr/bin/clang++-$llvm_version /usr/bin/c++

# Add environment variables directly to Dockerfile
ENV CC=/usr/bin/clang
ENV CXX=/usr/bin/clang++

# Copy test files and run the test script
COPY test/llvm/test.sh .
COPY test/llvm/test.cpp .

RUN chmod +x test.sh && ./test.sh

# Start an interactive bash shell
CMD ["/bin/bash"]
