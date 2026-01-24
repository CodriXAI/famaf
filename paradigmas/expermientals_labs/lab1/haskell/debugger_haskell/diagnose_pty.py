import subprocess
import time
import os
import select
import pty
import sys

# Create a pseudo-terminal
master, slave = pty.openpty()

print("Starting GHCi with PTY...")
process = subprocess.Popen(
    ['ghci', '-fno-diagnostics-show-caret', '-fprint-evld-with-show', 'test.hs'],
    stdin=slave, stdout=slave, stderr=slave,
    text=True, bufsize=0
)
os.close(slave) # Close slave in parent

def read_output(fd):
    out = ""
    while True:
        r, _, _ = select.select([fd], [], [], 0.1)
        if not r: break
        try:
            chunk = os.read(fd, 1024).decode('utf-8', errors='ignore')
            if not chunk: break
            out += chunk
        except OSError: break
    return out

time.sleep(1)
print(f"Initial: {repr(read_output(master))}")

commands = [":set prompt \"\"", ":break 6", "main", ":where", ":step", ":where"]

for cmd in commands:
    print(f"\nSending: {cmd}")
    os.write(master, (cmd + "\n").encode('utf-8'))
    time.sleep(0.5)
    output = read_output(master)
    print(f"Output: {repr(output)}")

process.terminate()
