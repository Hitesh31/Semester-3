note
	description: "Stable_marriage application root class"
	date: "$Date$"
	revision: "$Revision$"

class
	APPLICATION

inherit
	ARGUMENTS_32

create
	make

feature {NONE} -- Initialization
	n,ho:INTEGER
	temp,num:REAL
	arr:ARRAY2[INTEGER]
	make
			-- Run application.
		local
			i,j:INTEGER
		do
			input(ho)
			creatematrix(n)
			stablemarriage(n)
			rescue
				print("INVALID%N")
			retry
		end
		input(go:INTEGER)
		require
			true
		do
			Io.read_real
			num:=Io.last_real
			n:=num.truncated_to_integer
			ensure
				that: num>0 and num=n
		end
		creatematrix(no:INTEGER)
		require
			true
		local
			i,j:INTEGER
		do
			create arr.make(2*no,no+1)
			from
				i:=1
			invariant
				i>=1 and i<=2*no+1
			until
				i>2*no
			loop
				from
					j:=1
				invariant
					j>=1 and j<=no+2
				until
					j>no+1
				loop
					input_array(arr,i,j)
					j:=j+1
				end
				i:=i+1
			end
			ensure
				arr.height=2*no and arr.width=no+1
		end
		input_array(ar:ARRAY2[INTEGER];i:INTEGER;j:INTEGER)
		require
			true
		do
			Io.read_real
			temp:= Io.last_real
			arr[i,j]:=temp.truncated_to_integer
			ensure
				that: temp>0 and arr[i,j]=temp
		end
	otherpreferred(w:INTEGER;g:INTEGER;h:INTEGER):BOOLEAN
		require
			true and arr.height=2*n and arr.width=n+1
		local
			i,j:INTEGER
		do
			j:=1
			from
				i:=1
			invariant
				i>=1 and i<=n+1
			until
				i>n or j>n
			loop
				if
					arr[w,i+1]=h
				then
					result:=true
					i:=n
				end
				if
					arr[w,j+1]=g
				then
					result:=false
					j:=n
				end
				i:=i+1
				j:=j+1
			end
		end
		stablemarriage(no:INTEGER)
		require
			true and arr.height=2*no and arr.width=no+1
		local
			women:ARRAY[INTEGER]
			mfree:ARRAY[BOOLEAN]
			available,m,g,i,w,h,j:INTEGER
		do
			create women.make_filled(-1,1,no)
			create mfree.make_filled (false,1,no)
			from
				available:=no
			invariant
				available<=no and available>=0
			until
				available<1
			loop
				--print(available)
				--print("%N")
				from
					m:=1
				invariant
					m>=1 and m<=no+1
				until
					m>no
				loop
					if
						mfree[m]=false
					then
						g:=m
						m:=no
					end
					m:=m+1
				end
				from
					i:=1
				invariant
					i>=1 and i<=n+1
				until
					i>n or mfree[g]=true
				loop
					w:=arr[g,i+1]
					--print(w)
					if
						women[w]=-1
					then
						women[w]:=g
						mfree[g]:=true
						available:=available-1
						--print(available)
						--print("%N")
					else
						h:=women[w]
						if
							otherpreferred(w,g,h)=false
						then
							women[w]:=g
							mfree[g]:=true
							mfree[h]:=false
							--print(available)
							--print("%N")
						end
					end
					i:=i+1
				end
			end
			from
				j:=1
			invariant
				j>=1 and j<=n+1
			until
				j>n
			loop
				print(women[j])
				print("%N")
				j:=j+1
			end
		end

end
