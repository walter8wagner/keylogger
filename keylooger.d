import core.sys.windows.windows;
import std;
import std.process;

alias print = writeln;

void main() {

	print("hoal");
	spawnShell("pause");
}

/+
void main () {
	

	ShowWindow(GetConsoleWindow(), SW_HIDE);
	
    
	File file = File("archivo.txt" , "w");

	
	file.write("hla");
	
	file.close();
}

+/