import random


class Node:
    __slots__ = ("x", "y", "_evaluation", "action_id")

    def __init__(self, x, y, action_id=0):
        self.x = x
        self.y = y
        self._evaluation = self.x*self.y
        self.action_id = action_id

    def find_children(self):
        return [
                Node(self.x + 1, self.y, action_id=0),
                Node(self.x, self.y + 1, action_id=1),
            ]

    def random_child(self):
        return random.choice(self.find_children())

    def evaluation(self):
        return self._evaluation

    def is_terminal(self):
        return False

    def __lt__(self, other):
        return (self.x, self.y) < (other.x, other.y)

    def __eq__(self, other):
        return (self.x, self.y) == (other.x, other.y)

    def __hash__(self):
        return hash((self.x, self.y))

    def __repr__(self):
        return f"Node<self.x={self.x}, self.y={self.y}>"

    @staticmethod
    def get_action_space_size():
        return 2
