# Hofstadter-Conway $10,000 Sequence

A python script to compute the N-th [Hofstadter-Conway $10,000 sequence](https://en.wikipedia.org/wiki/Hofstadter_sequence#Hofstadter%E2%80%93Conway_$10,000_sequence).

## Usage

From the command line, run:

```bash
python3 hc10000.py 10000 # 5373
```

Or as a python module:

```python
from hc10000 import hofstadter_conway_10000

# 5054359020...7871534503 
print(hofstadter_conway_10000(10**100))
```

## Reference

T. Kubo and R. Vakil, [On Conway's recursive sequence](http://dx.doi.org/10.1016/0012-365X(94)00303-Z), Discr. Math. 152 (1996), 225-252.

In particular, the "Reduced frequency counts" section.
