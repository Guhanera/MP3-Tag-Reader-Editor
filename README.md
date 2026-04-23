🎵 MP3 Tag Reader (C Project)

📌 Overview
- MP3 Tag Reader is a command-line application developed in C.
- It reads and displays metadata (ID3 tags) from MP3 files.
- Supports multiple ID3 versions (ID3v1 and ID3v2, excluding v2.4).
- Helps users view and manage audio file information efficiently.
- Can be extended into a full-featured tag editor.

🎯 Objective
- Extract and display metadata from MP3 files.
- Understand ID3 tag structure and parsing.
- Provide editing capabilities for MP3 tag information.

🧠 Concept
- Uses file handling to read binary MP3 data.
- Parses ID3 metadata structures.
- Detects ID3 version before processing.
- Works with fixed-size (ID3v1) and frame-based (ID3v2) formats.

📚 About ID3 Tags
- ID3 is a metadata container used in MP3 files.
- Stores:
  - Title
  - Artist
  - Album
  - Track number
  - Year and comments

ID3v1
- Located at the end of the file.
- Fixed size: 128 bytes.
- Starts with identifier `"TAG"`.
- Fields include:
  - Title (30 bytes)
  - Artist (30 bytes)
  - Album (30 bytes)
  - Year (4 bytes)
  - Comment (30 bytes)
  - Genre (1 byte)

ID3v2
- Located at the beginning of the file.
- Flexible and frame-based structure.
- Starts with identifier `"ID3"`.
- Contains:
  - Header (version, flags, size)
  - Frames (metadata fields)

Frame Structure
- Frame ID (e.g., TIT2 → Title)
- Frame Size
- Flags
- Content (actual data)

⚙️ Features

📖 Display Metadata
- Detects ID3 version (v1 / v2).
- Displays all available tag information.
- Shows:
  - Title
  - Artist
  - Album
  - Year
  - Genre

✏️ Edit Tags
- Modify existing tag fields.
- Update metadata based on user input.

🖼️ Image Handling
- Detect embedded album art.
- Display image details:
  - Type
  - Size
  - Path (if applicable)

❗ Error Handling
- Displays proper error if:
  - No ID3 tag found
  - Invalid file format

ℹ️ Help Option
- `-h` option to display usage instructions.

🧾 Requirements
- Language: C
- Platform: Command-line (Linux/Windows)
- Concepts used:
  - File handling (binary)
  - Command-line arguments
  - Structures
  - Bit-level operations

🧪 Working Flow

Reading Tags
- Open MP3 file in binary mode.
- Detect ID3 version.
- Parse:
  - ID3v1 → fixed structure
  - ID3v2 → frame-based structure
- Display extracted metadata.

Editing Tags
- Select tag field.
- Modify value.
- Write updated data back to file.

Image Processing
- Identify embedded image frame.
- Extract and display metadata.

📊 Advantages
- Supports multiple ID3 versions.
- Provides detailed metadata extraction.
- Lightweight and efficient.
- Enhances understanding of file formats.

⚠️ Limitations
- Does not support ID3v2.4 (in current version).
- Limited UI (command-line only).
- Complex parsing for advanced tags.
