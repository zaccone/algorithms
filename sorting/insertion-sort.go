package main

import "fmt"

func printArr(in chan int, nl chan bool) {
	for {
		select {
		case n := <-in:
			fmt.Printf("%d ", n)
		case <-nl:
			fmt.Printf("\n")
		}
	}
}

func isort(c chan int) {

	arr := make([]int, 0, 0)
	nl := make(chan bool, 0)
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
		nl <- true
	}
}

func main() {
	arr := []int{5, 7, 4, 132, 5, 5, 87, 345, 6, 675, 567, 23, 445, 656, 776, 34, 534, 5}

	c := make(chan int)
	go isort(c)
	for _, item := range arr {
		c <- item
	}
	close(c)

	fmt.Printf("\n")
}
