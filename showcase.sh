#!/bin/bash

python3 src/python/commands.py > data/test.json
python3 src/python/simulation.py data/test.json