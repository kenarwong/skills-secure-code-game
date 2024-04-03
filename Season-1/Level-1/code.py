'''
Welcome to Secure Code Game Season-1/Level-1!

Follow the instructions below to get started:

1. tests.py is passing but code.py is vulnerable
2. Review the code. Can you spot the bug?
3. Fix the code but ensure that tests.py passes
4. Run hack.py and if passing then CONGRATS!
5. If stuck then read the hint
6. Compare your solution with solution.py
'''

#from collections import namedtuple
#
#Order = namedtuple('Order', 'id, items')
#Item = namedtuple('Item', 'type, description, amount, quantity')

# importing the module 
from typing import List, NamedTuple 
from decimal import Decimal
from decimal import getcontext

MAX_VALUE = Decimal('9' * getcontext().prec)

class Item(NamedTuple): 
    type: str
    description: str
    amount: Decimal
    quantity: int

class Order(NamedTuple): 
    id: int
    items: List[Item]

def toDecimal(value):
    try:
        return Decimal(str(value))
    except:
        raise ValueError("Invalid value: %s" % value)

def validorder(order: Order):
    print("Order ID:", order.id)
    print()

    net = toDecimal(0)

    #print("Max Value:", MAX_VALUE)

    for item in order.items:
        if item.type == 'payment':
            amount = toDecimal(item.amount)
            print("Item amount type:", type(amount))
            print("Item amount:", type(amount))

            net += amount
            print("Net value:", net)

        elif item.type == 'product':
            net -= toDecimal(item.amount) * toDecimal(item.quantity)
        else:
            return "Invalid item type: %s" % item.type

    if net != 0:
        return "Order ID: %s - Payment imbalance: $%0.2f" % (order.id, net)
    else:
        return "Order ID: %s - Full payment received!" % order.id