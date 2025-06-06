import json
import random

def generate_random_json(num_commands):
    roads = ["north", "south", "east", "west"]
    commands = []
    vehicle_count = 0

    for _ in range(num_commands):
        if random.random() < 0.9:  # 90% chance to add a vehicle
            vehicle_count += 1
            start, end = random.sample(roads, 2)  # Ensure start != end
            command = {
                "type": "addVehicle",
                "vehicleId": f"vehicle{vehicle_count}",
                "startRoad": start,
                "endRoad": end
            }
        else:
            command = {
                "type": "step"
            }
        commands.append(command)

    for _ in range(10):
        command = {
            "type": "step"
        }
        commands.append(command)

    result = {
        "commands": commands
    }

    return result

if __name__ == "__main__":
    random_json = generate_random_json(num_commands=100)
    print(json.dumps(random_json, indent=2))
