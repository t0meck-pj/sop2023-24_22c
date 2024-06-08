#!/bin/bash

echo $(($# > 1 ? "Pierwszy parametr: $1" : "Nie podano żadnych parametrów."))
