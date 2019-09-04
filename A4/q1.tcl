set ns [new Simulator]

$ns rtproto DV

set nf [open nam_q1.nam w]
$ns namtrace-all $nf

proc finish {} {
    global ns nf
    $ns flush-trace
    close $nf
    exec nam nam_q1.nam
    exit 0
}

for {set i 0} {$i < 3} {incr i} {
	set node($i) [$ns node]
}

set queuesize1 5
set queuesize2 10

set colors(0) Red
set colors(1) Blue
set colors(2) Orange
set colors(3) Black
set colors(4) Yellow
set colors(5) Green

$ns duplex-link $node(0) $node(1) 1Mb 10ms DropTail
$ns queue-limit $node(0) $node(1) $queuesize1
$ns duplex-link $node(0) $node(2) 512kb 10ms DropTail
$ns queue-limit $node(0) $node(2) $queuesize2

for {set i 1} {$i < 3} {incr i} {
    set node1 0
    set node2 $i
	set tcp_con [new Agent/TCP]
	$ns attach-agent $node($node1) $tcp_con
	$tcp_con set class_ $i

	set sink_node [new Agent/TCPSink]
	$ns attach-agent $node($node2) $sink_node
	$ns connect $tcp_con $sink_node

	$ns color $i $colors([expr ($i) % 6])
	$tcp_con set fid_ $i

	set ftp_con [new Application/FTP]
	$ftp_con attach-agent $tcp_con
	$ns at 0.1 "$ftp_con start"
	$ns at 1.5 "$ftp_con stop"
}
for {set i 1} {$i < 3} {incr i} {
    set node1 $i
    set node2 0
	set tcp_con [new Agent/TCP]
	$ns attach-agent $node($node1) $tcp_con
	$tcp_con set class_ $i

	set sink_node [new Agent/TCPSink]
	$ns attach-agent $node($node2) $sink_node
	$ns connect $tcp_con $sink_node

	$ns color $i $colors([expr ($i) + 2 % 6])
	$tcp_con set fid_ $i

	set ftp_con [new Application/FTP]
    $ftp_con set packetSize_ 20
    $ftp_con set rate_ 50Kb
	$ftp_con attach-agent $tcp_con
	$ns at 0.1 "$ftp_con start"
	$ns at 1.5 "$ftp_con stop"
}

$ns at 2.0 "finish"
$ns run