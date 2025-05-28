import json
import sys
import subprocess

def parse_commands(filename):
    try:
        with open(filename, 'r', encoding='utf-8') as file:
            data = json.load(file)

        lines = [
            ' '.join(f'{value}' for key, value in command.items())
            for command in data.get("commands", [])
        ]

        return '\n'.join(lines)

    except Exception as e:
        sys.stderr.write(f"Błąd: {e}\n")
        sys.exit(1)

def parse_step_result_output(output_lines):
    step_statuses = []

    for line in output_lines:
        parts = line.strip().split()
        if not parts or parts[0] != "step_result":
            continue  # pomiń niepoprawne linie
	
        step_statuses.append({
            "leftVehicles": parts[1:]
        })

    return {"stepStatuses": step_statuses}


def main():
    if len(sys.argv) < 2:
        print("Użycie: python main_script.py <plik_json>")
        sys.exit(1)

    json_file = sys.argv[1]
    target_script = "bin/sim"

    parsed_output = parse_commands(json_file)

    # Uruchomienie drugiego skryptu i przekazanie danych przez stdin
    process = subprocess.Popen(
        ["./"+target_script],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True
    )
    stdout_data, stderr_data = process.communicate(input=parsed_output)

    if stderr_data:
        print(stderr_data, file=sys.stderr)
    
    output_lines = stdout_data.strip().splitlines()
    final_result = parse_step_result_output(output_lines)

    # Wypisz wynik jako JSON
    print(json.dumps(final_result, indent=2))


if __name__ == "__main__":
    main()

