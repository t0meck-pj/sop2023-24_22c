#!/bin/bash

if [[ $0 =~ \.sh$ ]]; then
    echo „Jest .sh"
else
    echo "Nazwa skryptu nie kończy się .sh."
    mv "$0" "$0.sh"
fi



#reszty nie potrafilem zrobic
