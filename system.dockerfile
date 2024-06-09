FROM debian:12

##################################
#######		DEBIAN LLVM	  ########
##################################

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
RUN export LLVM_VERSION=$(ls /usr/bin | grep clang++ | tr -d 'clang++-'); \
	export LLVM_ROOT=$(llvm-config-$LLVM_VERSION --prefix); \
    for bin in $LLVM_ROOT/bin/*; do \
      bin=$(basename $bin); \
      if test -f /usr/bin/$bin-$LLVM_VERSION ; then \
        ln -sf /usr/bin/$bin-$LLVM_VERSION /usr/bin/$bin; \
      fi; \
    done; \
	rm -f /usr/bin/cc; \
	ln -sf /usr/bin/clang-$LLVM_VERSION /usr/bin/cc; \
	ln -sf /usr/bin/clang++-$LLVM_VERSION /usr/bin/c++;

# Add environment variables directly to Dockerfile
ENV CC=/usr/bin/clang
ENV CXX=/usr/bin/clang++

COPY test/llvm/test.sh .
COPY test/llvm/test.cpp .

RUN chmod +x test.sh && ./test.sh

##################################
######  ANTLR & STD PCM DEPS #####
##################################

# Copy all files
COPY . /project/

# Set the working directory for the third-party build
WORKDIR /project/third-party

# Install wget, curl, jq, and other dependencies
RUN apt-get update && apt-get install -y wget curl jq openjdk-17-jre-headless

RUN ls

# Fetch the latest ANTLR release tag from GitHub, download the jar file and create aliases
RUN ANTLR_VERSION=$(cat .versions/antlr) && \
    wget http://www.antlr.org/download/antlr-$ANTLR_VERSION-complete.jar -O /usr/local/lib/antlr-$ANTLR_VERSION-complete.jar && \
    echo '#! /bin/bash\n'\
'export CLASSPATH=".:/usr/local/lib/antlr-'$ANTLR_VERSION'-complete.jar:$CLASSPATH"\n'\
'java -jar /usr/local/lib/antlr-'$ANTLR_VERSION'-complete.jar "$@"\n'\
> /usr/local/bin/antlr4 && \
    chmod +x /usr/local/bin/antlr4 && \
	ln -s $(which antlr4) /usr/bin/antlr

# Build project deps
RUN make

# Start an interactive bash shell
CMD ["/bin/bash"]
