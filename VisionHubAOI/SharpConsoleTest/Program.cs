using System.Runtime.CompilerServices;
using static System.Collections.Specialized.BitVector32;

namespace SharpConsoleTest
{
    internal class Program
    {
        static void Main(string[] args)
        {
            try
            {

                var engine = VisionHub.V1.Engine.Create();
                engine.TraceEvent += Engine_TraceEvent;
                engine.LineEvent += Engine_LineEvent;
                engine.SnapShotEvent += Engine_SnapShotEvent;


                engine.AddLibrary("VisionHubAOI.Plugin.OpenCV.dll");

                engine.LoadPlugin("E:\\Github\\visionhubaoi\\VisionHubAOI\\SharpConsoleTest\\bin\\x64\\Debug\\net8.0-windows\\Plugins");


                engine.Compile("E://test.txt");

                engine.Mode = VisionHub.V1.ExecMode.Run;
                engine.Run();


                using var output = engine.Output();



                System.Console.WriteLine("test");
            }
            catch (Exception ex)
            {
                System.Diagnostics.Debug.WriteLine(ex.ToString());
            }
        }

        private static void Engine_SnapShotEvent(VisionHub.V1.SnapShot snapShot)
        {


            System.Console.WriteLine("test");
        }

        private static void Engine_LineEvent(int row, int col, string message)
        {
            System.Console.WriteLine("[{0}][{1}]:{2}", row, col, message);
        }

        private static void Engine_TraceEvent(VisionHub.V1.TraceType type, int row, int col, string section, string message)
        {

            string errorType = type == VisionHub.V1.TraceType.Error ? "ERROR" :
                               type == VisionHub.V1.TraceType.Warnning ? "WARN" : "INFO";

            System.Console.WriteLine("[{0}][{1}][{2},{3}]:{4}", errorType, row, col, section, message);
        }
    }
}
