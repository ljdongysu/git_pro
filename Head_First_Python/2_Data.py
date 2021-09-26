book = "The Hitchhiker's Guide to the Galaxy"
booklist = list(book)
print(booklist)

bookwards = booklist[::-1]
print(''.join(bookwards))


a = [0,1,2,3,4,5,6]
print(a[3::2])


paranoid_android = "Marvin, the Paranoid Android"
letters = list(paranoid_android)
for char in letters[:6]:
    print('\t',char)
print()
for char in letters[-7:]:
    print('\t'*2,char)
print()
for char in letters[12:20]:
    print('\t'*3,char)
    