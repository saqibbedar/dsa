# Use base image
FROM gcc:latest

# Set working directory
WORKDIR /app

# Copy source code
COPY info.cpp .

# Compile C++ program
RUN g++ -o info info.cpp

# Execute .exe file
CMD [ "./info" ]