LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
ENTITY sipo_tb IS
END sipo_tb;

ARCHITECTURE behavior OF sipo_tb IS

    -- Component Declaration for the Unit Under Test (UUT)
    COMPONENT sipo
    PORT(
         clk, clear : in std_logic;
         Input_Data: in std_logic;
         Q: out std_logic_vector(3 downto 0)
        );
    END COMPONENT;

      --Inputs
      signal Input_Data : std_logic := '1';
      signal clk : std_logic := '0';
      signal clear : std_logic :='0';
      --Outputs
      signal Q : std_logic_vector(3 downto 0) := "0000";

   -- Clock period definitions
   --constant clk_period : time := 10 ns;

BEGIN
      -- Instantiate the Unit Under Test (UUT)
   uut: sipo PORT MAP (
          clk => clk,
          Input_Data => Input_Data,
          Q => Q,
          clear=>'0'
        );

   -- Clock process definitions
--   clk_process : process
--   begin
--      clk <= '0';
--      wait for clk_period/2;
--      clk <= '1';
--      wait for clk_period/2;
--   end process;

    -- Stimulus process
   --if it works it works
   stim_proc: process
   begin
   clk <='0';
   Input_Data<='0';
   wait for 10 ns;      
   clk<='0';
   wait for 10 ns;      
   clk <='1';
   Input_Data<='0';
   wait for 10 ns;      
   clk<='0';
   wait for 10 ns;      
   clk <='1';
   Input_Data<='1';
   wait for 10 ns;      
   clk<='0';   
   wait for 10 ns;      
   clk <='1';
   Input_Data<='0';
   wait for 10 ns;      
   clk<='0';
   wait for 10 ns;      
   clk <='1';
   Input_Data<='0';
   wait for 10 ns;      
   clk<='0';
   wait;
   wait;
   end process;
END;

--END;