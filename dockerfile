# syntax = edrevo/dockerfile-plus
INCLUDE+ debian-llvm.dockerfile

# Copy third-party directory first to leverage caching
COPY third-party /project/third-party

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
