object Try{
	def main(args:Array[String])
	{
		println("Enter Array Elements: ")
	val l=readLine.split(" ").map(_.toInt)
	println("\nKuthla Element Search Karaychay: ")

	val s:Int=readLine.toInt
	val st:Int=Search(s,l)

	if(st!= -1)
	println("Element at position:"+st)
	else
	println("Element nahiye")

	}

	def Search(target:Int,l:Array[Int]) ={
		
		def recu(low:Int,high:Int):Integer = low+high/2 match{
			case _ if high < low => -1;
			case mid if l(mid)> target => recu(low,mid-1)
			case mid if l(mid)< target => recu(mid+1,high)
			case mid => mid
		}
		recu(0,l.size-1)
	}
}