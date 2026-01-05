import threading
import time

# Shared buffer (stores particles)
buffer = []

# Semaphores (initial values)
empty = threading.Semaphore(100)   # 100 empty particle slots
full = threading.Semaphore(0)      # 0 particles initially
mutex = threading.Lock()           # mutual exclusion


def producer(producer_id):
    while True:
        # Produce a particle pair
        P1 = f"P{producer_id}-1"
        P2 = f"P{producer_id}-2"

        # Need 2 empty slots
        empty.acquire()
        empty.acquire()

        mutex.acquire()
        buffer.append(P1)
        buffer.append(P2)
        print(f"Producer {producer_id} produced {P1}, {P2}")
        mutex.release()

        # Signal that 2 particles are available
        full.release()
        full.release()

        time.sleep(1)


def consumer():
    while True:
        # Need 2 particles
        full.acquire()
        full.acquire()

        mutex.acquire()
        P1 = buffer.pop(0)
        P2 = buffer.pop(0)
        print(f"Consumer packaged {P1}, {P2}")
        mutex.release()

        # Free 2 slots
        empty.release()
        empty.release()

        time.sleep(2)


# Create threads
p1 = threading.Thread(target=producer, args=(1,))
p2 = threading.Thread(target=producer, args=(2,))
c = threading.Thread(target=consumer)

# Start threads
p1.start()
p2.start()
c.start()
