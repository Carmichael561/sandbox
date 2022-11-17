 
alias enum="sed 's/[a-z]/\U&/g' | sed 's/ /_/g'"

# sed -e "s/[[:space:]]\+/ /g"            - replace all tabs and spaces with a single space
# sed 's/\([^ ]*\) *\(.*\)/\2 \1/'        - sed move first (\1) column to end (\2)
