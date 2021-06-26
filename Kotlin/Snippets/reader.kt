import java.util.StringTokenizer
import java.io.InputStreamReader
import java.io.BufferedReader
import java.io.InputStream

private fun readLn() = readLine()!! // string line
private fun readInt() = readLn().toInt() // single int
private fun readLong() = readLn().toLong() // single long
private fun readDouble() = readLn().toDouble() // single double
private fun readStrings() = readLn().split(" ") // list of strings
private fun readInts() = readStrings().map { it.toInt() } // list of ints
private fun readLongs() = readStrings().map { it.toLong() } // list of longs
private fun readDoubles() = readStrings().map { it.toDouble() } // list of doubles

private val OUTPUT_LINES = mutableListOf<String>()
private fun outputLn(s: String) { OUTPUT_LINES += s }

fun main() {
	R.init(System.`in`)
	print(OUTPUT_LINES.joinToString("\n"))
}

internal object R {
    private lateinit var reader: BufferedReader
    private lateinit var tokenizer: StringTokenizer
    fun init(input: InputStream) {
        reader = BufferedReader(InputStreamReader(input))
        tokenizer = StringTokenizer("")
    }

    fun next(): String {
        while (!tokenizer.hasMoreTokens()) tokenizer = StringTokenizer(reader.readLine())
        return tokenizer.nextToken()
    }
 
    fun nextInt() = next().toInt()
    fun nextDouble() = next().toDouble()
    fun nextLong() = next().toLong()
}