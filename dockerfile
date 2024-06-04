# syntax = edrevo/dockerfile-plus
INCLUDE+ debian-llvm.dockerfile

# Install system deps
RUN apt-get install -y antlr4
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
