-- FPGA projects using VHDL/ VHDL 
-- fpga4student.com
-- VHDL code for D Flip FLop
-- VHDL code for rising edge D flip flop 
Library IEEE;
USE IEEE.Std_logic_1164.all;

entity dff is 
   port(
      Q : out std_logic;    
      Clk :in std_logic;
      clr : in std_logic;   
      D :in  std_logic    
   );
end dff;
architecture Behavioral of dff is  
begin  
 process(Clk, clr)
 begin
    if(clr='1') then
        Q <= '1';--bodged to work by adding not change to 0 if using elsewhere!!
    elsif(rising_edge(Clk)) then
        Q <= D; 
    end if;
    --Q <= not Q;       
 end process;  
end Behavioral; 