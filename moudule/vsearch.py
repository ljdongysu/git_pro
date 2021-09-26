def search4vowels(phrase: str) -> set:
    """Return any vowels found in supplied pharse."""
    vowels = set('aeiou')
    return vowels.intersection(set(phrase))


def search4letters(phrase: str, letters: str='aeiou') -> set:
    """Return a set of the 'letters' found in 'phrase'."""
    return set(letters).intersection(set(phrase))


# help(search4letters)
# print(search4letters('hitch-hiker','aeiou'))
# print(search4letters('galaxy','xyz'))
# print(search4letters('life, the universe,and everything','o'))
