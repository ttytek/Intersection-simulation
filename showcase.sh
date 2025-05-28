#!/bin/bash

make
python3 src/python/commands.py > data/in.json
python3 src/python/simulation.py data/in.json 1> data/out.json