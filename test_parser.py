import sys

sys.path.append("D:/Projects/eu4gamereview/EU4GameReview/build")

import eu4tools

data = eu4tools.parse(
    "C:\\Users\\Taha\\Documents\\Paradox Interactive\\Europa Universalis IV\\save games\\zoroaustrianss.eu4"
)
print(type(data))
print(list(data.keys())[:10])
