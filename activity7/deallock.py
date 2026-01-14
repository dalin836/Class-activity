 # no_deadlock_version.py
import threading
import time

print_lock = threading.Lock()

class Account:
    def __init__(self, name, balance):
        self.name = name
        self.balance = balance
        self.lock = threading.Semaphore(1)

account1 = Account("Account1", 1000)
account2 = Account("Account2", 1000)

def safe_print(msg):
    with print_lock:
        print(msg, flush=True)

def transfer(from_account, to_account, amount):
    # Acquire locks in consistent order (alphabetical by name)
    first, second = sorted([from_account, to_account], key=lambda x: x.name)
    safe_print(f"{threading.current_thread().name} locking {first.name}")
    first.lock.acquire()
    time.sleep(1)
    safe_print(f"{threading.current_thread().name} locking {second.name}")
    second.lock.acquire()
    safe_print(f"{threading.current_thread().name} transferring {amount}")
    from_account.balance -= amount
    to_account.balance += amount
    second.lock.release()
    first.lock.release()

t1 = threading.Thread(target=transfer, name="Thread-1", args=(account1, account2, 100))
t2 = threading.Thread(target=transfer, name="Thread-2", args=(account2, account1, 200))

t1.start()
t2.start()
t1.join()
t2.join()

print(f"Final balances: Account1={account1.balance}, Account2={account2.balance}")
