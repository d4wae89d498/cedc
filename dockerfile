# syntax = edrevo/dockerfile-plus
INCLUDE+ debian-llvm.dockerfile

# Grap packages version of locally installed ones
RUN ANTLR_VERSION=$(cd third-party/antlr && git describe --tags | grep -oP '^[0-9]+\.[0-9]+\.[0-9]+') && \
    LLVM_VERSION=$(cd third-party/llvm-project && git describe --tags | grep -oP '(?<=llvmorg-)[0-9]+') \
    echo "export ANTLR_VERSION=$ANTLR_VERSION" >> /etc/profile && \
    echo "export LLVM_VERSION=$LLVM_VERSION" >> /etc/profile


# Install wget, curl, jq, and other dependencies
RUN apt-get update && apt-get install -y wget curl jq openjdk-17-jre-headless

# Fetch the latest ANTLR release tag from GitHub and download the jar file
RUN LATEST_VERSION=$ANTLR_VERSION  && \
    wget http://www.antlr.org/download/antlr-$ANTLR_VERSION-complete.jar -O /usr/local/lib/antlr-$ANTLR_VERSION-complete.jar && \
    echo '#! /bin/bash\n'\
'export CLASSPATH=".:/usr/local/lib/antlr-'$ANTLR_VERSION'-complete.jar:$CLASSPATH"\n'\
'java -jar /usr/local/lib/antlr-'$ANTLR_VERSION'-complete.jar "$@"\n'\
> /usr/local/bin/antlr4 && \
    chmod +x /usr/local/bin/antlr4

# Verify the installation by printing ANTLR version
RUN ln -s /usr/local/bin/antlr4 /usr/bin/antlr4
RUN ln -s $(which antlr4) /usr/bin/antlr

# Copy third-party directory first to leverage caching
COPY third-party /project/third-party
COPY common.mk /project/common.mk

# Set the working directory for the third-party build
WORKDIR /project/third-party

# Build the third-party dependencies
RUN make

# Copy the main project files
COPY . /project/

# Set the working directory for the main project
WORKDIR /project/

# Build the main project
RUN make

# Run the tests
RUN make test
