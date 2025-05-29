#!/bin/bash

make
mkdir data
python3 src/python/commands.py > data/in.json
python3 src/python/simulation.py data/in.json 1> data/out.json
