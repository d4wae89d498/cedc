# syntax=docker.io/docker/dockerfile:1.7-labs
FROM whitehat101/cedc-system

# Copy the main project files
COPY --exclude=third-party . /project/

# Set the working directory for the main project
WORKDIR /project/

# Compiles the app
RUN make
