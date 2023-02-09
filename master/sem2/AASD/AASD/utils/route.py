from typing import List, Optional
from dataclasses import dataclass
from utils.cords import Cords
from aioxmpp import JID


@dataclass
class Target:
    cords: Cords
    jid: JID
    est_rubbish_volume: float


@dataclass
class Route:
    targets: List[Target]

    def __init__(self, targets: List[Target]):
        self.targets = targets

    def estimate_distance(self, start: Cords) -> float:
        dist = 0
        curr_cords = start
        for target in self.targets:
            dist += target.cords.dist(curr_cords)
            curr_cords = target.cords
        return dist

    def estimate_rubbish_volume(self) -> float:
        volume = 0
        for target in self.targets:
            volume += target.est_rubbish_volume
        return volume

    def last_target(self) -> Target:
        return self.targets[-1]

    def curr_target(self) -> Optional[Target]:
        return self.targets[0] if self.targets else None

    def pop(self):
        self.targets.pop(0)

    def extend(self, other):
        self.targets.extend(other.targets)

    def __bool__(self):
        return bool(self.targets)
