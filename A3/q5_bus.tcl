set ns [new Simulator]
set colors(0) Red
set colors(1) Blue
set colors(2) Black
set colors(3) Pink
set colors(4) Yellow
set colors(5) Green

set f [open problem5.nam w]
$ns namtrace-all $f

proc finish {} {
    global ns f
    $ns flush-trace
    close $f
    
    exec nam problem5.nam &
    exit 0
}
set input [gets stdin]
scan $input "%d %d" N k
set n(0) [$ns node]
set y "$n(0)"
for {set i 1} {$i < $N} {incr i} {
    set n($i) [$ns node]
    append y " "
    append y "$n($i)"
}
puts $y
puts "$n(0) $n(1)"
$ns make-lan $y 0.5Mb 40ms LL Queue/DropTail Mac/802_3
for {set i 0} {$i < $k} {incr i} {
    set input [gets stdin]
	scan $input "%d %d" i1 i2
    set tcp [new Agent/TCP]
    $tcp set class_ [expr $i%5]
    $ns attach-agent $n($i1) $tcp

    set sink [new Agent/TCPSink]
    $ns attach-agent $n($i2) $sink
    $ns connect $tcp $sink
   	$ns color $i $colors([expr ($i) % 6])
    $tcp set fid_ $i

    set ftp($i) [new Application/FTP]
    $ftp($i) attach-agent $tcp
    # $ftp($i) set type_ FTP

    $ns at 0.1 "$ftp($i) start"
	$ns at 1.5 "$ftp($i) stop"
}
# for {set i 0} {$i < $k} {incr i} {
#     $ns at [expr ($i/10)+0.1] "$ftp($i) start"
#     $ns at [expr ($i/10)+1.5] "$ftp($i) stop"
# }
# $ns at [expr ($k/10)+1.5] "finish"
$ns at 2.0 "finish"
$ns run