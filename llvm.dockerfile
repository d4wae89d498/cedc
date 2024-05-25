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

# Detect llvm version and create clang alias
RUN llvm_version=$(ls /usr/bin | grep clang++ | tr -d 'clang++-') \
    && echo "alias clang='clang-$llvm_version'" >> /root/.bashrc \
    && echo "alias clang++='clang++-$llvm_version'" >> /root/.bashrc \
    && echo "export CC=/usr/bin/clang-$llvm_version" >> /root/.bashrc \
    && echo "export CXX=/usr/bin/clang++-$llvm_version" >> /root/.bashrc

# Bash as default shell
SHELL ["/bin/bash", "-c"]

# Clone and build libcxx to have std BMI
RUN git clone https://github.com/llvm/llvm-project.git
RUN . /root/.bashrc \
	&& cd llvm-project \
    && mkdir build \
    && cmake -G Ninja -S runtimes -B build -DLLVM_ENABLE_RUNTIMES="libcxx;libcxxabi;libunwind" \
    && ninja -C build

# Start an interactive bash shell
CMD ["/bin/bash", "-c", "echo 12"]
