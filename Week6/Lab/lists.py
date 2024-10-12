l = [1,2,3,4,5,6,7,8,9,0]
print("The original list is:")
print(l)
print()

print("l[:2] returns: ")
print(l[:2])
print()

print("l[-2] returns: ")
print(l[-2])
print()

print("l[:-2] returns: ")
print(l[:-2])
print()

print("l[8:] returns: ")
print(l[8:])
print()


print("l[-2:] returns: ")
print(l[-2:])
print()


print("l[int(i) in \"12345\"] returns: ")
for i in "12345":
    print(l[int(i)], end=" ")
print(end="\n\n")

print(l[int(i)] in "12345", end=" ")
