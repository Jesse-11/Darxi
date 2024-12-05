# Stage 1: Build environment
FROM ubuntu:22.04 AS builder

# Set environment variables to reduce interactions and improve speed
ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=UTC

# Install essential packages in a single RUN command
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    qt6-base-dev \
    libqt6sql6-sqlite \
    git \
    libxcb-xinerama0 \
    libxcb-icccm4 \
    libxcb-image0 \
    libxcb-keysyms1 \
    libxcb-render-util0 \
    libxcb-xkb1 \
    libgl1-mesa-dev \
    libglu1-mesa-dev \
    && rm -rf /var/lib/apt/lists/*

# Copy only the files needed for cmake configuration first
WORKDIR /app
COPY CMakeLists.txt .
COPY src/ src/
COPY include/ include/
COPY resources/ resources/

# Build the application
RUN mkdir -p build && \
    cd build && \
    cmake .. && \
    make -j$(nproc)

# Stage 2: Runtime environment
FROM ubuntu:22.04

# Install only runtime dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    libqt6core6 \
    libqt6gui6 \
    libqt6widgets6 \
    libqt6sql6-sqlite \
    libxcb-xinerama0 \
    libxcb-icccm4 \
    libxcb-image0 \
    libxcb-keysyms1 \
    libxcb-render-util0 \
    libxcb-xkb1 \
    && rm -rf /var/lib/apt/lists/*

# Create a non-root user
RUN useradd -m -s /bin/bash appuser
USER appuser

# Copy only the built application from builder
WORKDIR /app
COPY --from=builder --chown=appuser:appuser /app/build/Darxi_Networking .
COPY --chown=appuser:appuser resources/ resources/

EXPOSE 8080
CMD ["./Darxi_Networking"]
