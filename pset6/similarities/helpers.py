import nltk


def lines(a, b):
    """Return lines in both a and b"""
    # Make sets from lines
    setA = set(a.splitlines())
    setB = set(b.splitlines())
    # Make set of unique lines
    result = list(setA & setB)

    return result


def sentences(a, b):
    """Return sentences in both a and b"""
    # Make sets from sentences
    setA = set(nltk.sent_tokenize(a))
    setB = set(nltk.sent_tokenize(b))
    # Make set of unique sentences
    result = list(setA & setB)

    return result


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    # Make sets
    setA = set()
    setB = set()

    # Fill sets with subsrings
    for i in range(len(a) + 1 - n):
        setA.add(a[i:i+n])

    for i in range(len(b) + 1 - n):
        setB.add(b[i:i+n])

    # Make set of unique substrings
    result = list(setA & setB)

    return result
