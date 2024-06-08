#!/bin/bash

print_colored_text() {
    local text="$1"
    local color="$2"

    case "$color" in
        "red")
            color_code="\e[31m"
            ;;
        "green")
            color_code="\e[32m"
            ;;
        "yellow")
            color_code="\e[33m"
            ;;
        "blue")
            color_code="\e[34m"
            ;;
        *)
            echo "Nieznany kolor"
            return 1
            ;;
    esac

    echo -e "${color_code}${text}\e[0m"
}

print_colored_text "olek" "red"
print_colored_text "olek" "green"
print_colored_text "olek" "yellow"
print_colored_text "olek" "blue"
