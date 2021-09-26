person3 = {'Name': 'Ford Perfect',
           'Gender': 'Male',
           'Occupation': 'Researcher',
           'Home Plaent': 'Betelguse Seven'}
print(person3)

found = {}
found['a'] = 0
found['u'] = 0
found['e'] = 0
found['i'] = 0
found['o'] = 0

print(found)

for key in found:
    print(key,'was found', found[key])
for key in sorted(found):
    print(key,'was found', found[key])
print(found.items())
