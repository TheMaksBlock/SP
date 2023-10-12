sort -t: people > sorted_people
sort -t: people1 > sorted_people1

comm -3 sorted_people sorted_people1 > uncommon

echo "Файл с уникальными словами создан"

