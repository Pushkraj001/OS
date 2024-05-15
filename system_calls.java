import java.io.*;
import java.nio.file.*;
import java.nio.file.attribute.*;

public class system_calls {
    public static void main(String[] args) {
        // Process-related system calls
        System.out.println("Parent process (PID: " + ProcessHandle.current().pid() + ")");

        try {
            ProcessBuilder pb = new ProcessBuilder();
            pb.command("bash", "-c", "echo \"Child process (PID: $$, Parent PID: $PPID)\"");
            Process childProcess = pb.start();
            int exitCode = childProcess.waitFor();
            System.out.println("Child process has finished with exit code: " + exitCode);
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }

        // File-related system calls
        try {
            PrintWriter writer = new PrintWriter("example.txt");
            writer.println("Hello, world!");
            writer.close();

            BufferedReader reader = new BufferedReader(new FileReader("example.txt"));
            String line = reader.readLine();
            System.out.println("Read from file: " + line);
            reader.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

        // Protection-related system call
        try {
            Files.setPosixFilePermissions(Paths.get("example.txt"),
                                           PosixFilePermissions.fromString("rw-r--r--"));
            System.out.println("File permissions changed successfully");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
