package main

import (
	"fmt"
	"sync"
)

var wg sync.WaitGroup

const (
	CLOSE   = 1
	NEWLINE = 2
)

func printArr(in chan int, nl chan int) {
	wg.Add(1)
	defer wg.Done()
	for {
		select {
		case number := <-in:
			fmt.Printf("%d ", number)
		case other := <-nl:
			if other == NEWLINE {
				fmt.Printf("\n")
			} else {
				return
			}
		}
	}
}

func isort(c chan int) {
	wg.Add(1)
	defer wg.Done()
	arr := make([]int, 0, 0)
	nl := make(chan int, 0)
	in := make(chan int, 0)

	size := 0
	go printArr(in, nl)
	for i := range c {
		arr = append(arr, i)
		size++
		j := size - 1

		for j > 0 && arr[j-1] > arr[j] {
			arr[j-1], arr[j] = arr[j], arr[j-1]
			j--
		}
		for _, it := range arr {
			in <- it
		}
		nl <- NEWLINE
	}
	nl <- CLOSE
}

func main() {
	arr := []int{5, 7, 4, 132, 5, 5, 87, 345, 6, 675, 567, 23, 445, 656, 776, 34, 534, 5}

	c := make(chan int)
	go isort(c)
	for _, item := range arr {
		c <- item
	}
	close(c)
	wg.Wait()
	fmt.Printf("\n")
}
