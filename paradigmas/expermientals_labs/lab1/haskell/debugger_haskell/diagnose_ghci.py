import subprocess
import time
import fcntl
import os
import select

def read_output(process):
    out = ""
    while True:
        r, _, _ = select.select([process.stdout], [], [], 0.1)
        if not r: break
        try:
            chunk = process.stdout.read(1024)
            if not chunk: break
            out += chunk
        except: break
    return out

print("Starting GHCi...")
process = subprocess.Popen(
    ['ghci', '-fno-diagnostics-show-caret', '-fprint-evld-with-show', 'test.hs'],
    stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
    text=True, bufsize=0
)

# Non-blocking
fd = process.stdout.fileno()
fl = fcntl.fcntl(fd, fcntl.F_GETFL)
fcntl.fcntl(fd, fcntl.F_SETFL, fl | os.O_NONBLOCK)

time.sleep(1)
print(f"Initial: {read_output(process)}")

commands = [":set prompt \"\"", "b 6", "main", ":where", "s", ":where"]

for cmd in commands:
    print(f"\nSending: {cmd}")
    process.stdin.write(f"{cmd}\n")
    process.stdin.flush()
    time.sleep(0.5)
    output = read_output(process)
    print(f"Output: {repr(output)}")

process.terminate()
