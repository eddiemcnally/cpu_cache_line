mydata = read.csv("../data/affinity_maxpri.csv")
vals<-c(mydata$X)
plot(vals, type="l", xlab="Sample #", ylab="Time (ticks)", ylim=c(100, 600))
title("CPU Affinity, MAX_PRIO")

mydata = read.csv("../data/no_affinity_maxpri.csv")
vals<-c(mydata$X)
plot(vals, type="l", xlab="Sample #", ylab="Time (ticks)", ylim=c(100, 600))
title("NO CPU Affinity, MAX_PRIO")

mydata = read.csv("../data/no_affinity_normpri.csv")
vals<-c(mydata$X)
plot(vals, type="l", xlab="Sample #", ylab="Time (ticks)", ylim=c(100, 600))
title("NO CPU Affinity, Norm PRI")

mydata = read.csv("../data/affinity_normpri.csv")
vals<-c(mydata$X)
plot(vals, type="l", xlab="Sample #", ylab="Time (ticks)", ylim=c(100, 600))
title("CPU Affinity, Norm PRI")
