import sys
import time

sys.path.append("D:/Projects/eu4gamereview/EU4GameReview/build")

import eu4tools  # type: ignore

start = time.time()
data = eu4tools.parse(
    "C:\\Users\\Taha\\Documents\\Paradox Interactive\\Europa Universalis IV\\save games\\zoroaustrianss.eu4"
)
end = time.time()
print(f"Parsing took {end - start:.2f} seconds")

print(type(data))
print(list(data["countries"]["HAB"]["army"]))
