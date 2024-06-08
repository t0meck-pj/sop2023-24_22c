#!/bin/bash
a="SOP! SOP w imieniu prawa! SOP w imieniu prawa!"
b="\e[32mSOP\e[0m"
echo -e ${a//SOP/$b}
