# Check if X server is running
if ! xset q &>/dev/null; then
    echo "No X server running. Please start X server first."
    exit 1
fi

# Allow X server connections
xhost +local:docker

# Build and run the container
docker-compose build
docker-compose up

# Clean up X server permissions
xhost -local:docker