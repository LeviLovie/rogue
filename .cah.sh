#/bin/bash
# Creates a header file for every asset in src/assets from assets/. And combines it all together into a single header file.

# Row assets directory
rad="./assets"
# Header assets directory
had="./src/assets"
chaf="./src/aseets/assets.h"

# Check directories exists
if [ ! -d "$rad" ]; then
  echo "Directory not found: $rad"
  exit 1
fi
if [ -d "$had" ]; then
  rm -R "$had"
fi
mkdir "$had"

# Function to process a file and create a header
function process_file {
  relative_path="${1#./assets/}"
  mkdir -p "$had/$(dirname "$relative_path")"

  # Process the file and create the header in the corresponding directory
  xxd -i "$1" "$had/${relative_path}.h"
  echo "Processed $1 to $had/${relative_path}.h"
}

# Function to recursively process directories
function process_directory {
  local dir=$1
  local combined_file="$had/${dir#./assets/}.h"

  for entry in "$dir"/*; do
    if [ -d "$entry" ]; then
      process_directory "$entry"
    elif [ -f "$entry" ]; then
      process_file "$entry"
      cat "$had/${entry#./assets/}.h" >>"$combined_file"
    fi
  done
  echo "Combined $had/${entry#./assets/}.h into $combined_file\n"
}

# Iterate through all files in RAD directory (including subdirectories)
process_directory "$rad"

# Combine all header files into a single header file
cat "$had"/*.h >"$chaf"
echo "Combined all header files into $chaf"
