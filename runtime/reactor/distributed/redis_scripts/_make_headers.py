import os
import subprocess

INPUT_DIR = "."
OUTPUT_DIR = "_headers"

def process_line(line: str) -> str:
    if line.startswith("unsigned char"):
        line = line.replace("unsigned char", "constexpr char")
    if line.startswith("unsigned int"):
        line = line.replace("unsigned int", "constexpr unsigned int")

    return line


def main():
    os.makedirs(OUTPUT_DIR, exist_ok=True)

    for filename in os.listdir(INPUT_DIR):
        if filename.endswith(".lua") and os.path.isfile(filename):
            input_path = os.path.join(INPUT_DIR, filename)

            base_name = os.path.splitext(filename)[0]
            output_file = f"{base_name}_lua.hpp"
            output_path = os.path.join(OUTPUT_DIR, output_file)

            try:
                result = subprocess.run(
                    ["xxd", "-i", input_path],
                    capture_output=True,
                    text=True,
                    check=True
                )

                lines = result.stdout.splitlines()

                with open(output_path, "w") as out:
                    for line in lines:
                        processed = process_line(line)
                        out.write(processed + "\n")

                print(f"Generated: {output_path}")

            except subprocess.CalledProcessError as e:
                print(f"Error processing {filename}: {e}")


if __name__ == "__main__":
    main()